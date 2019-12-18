#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
typedef  char uint64_t ;
typedef  int /*<<< orphan*/  timestamp ;
struct user_pass {char* username; } ;
struct TYPE_3__ {int /*<<< orphan*/ * hmac; } ;
struct TYPE_4__ {TYPE_1__ auth_token_key; } ;
struct tls_multi {char* auth_token; int auth_token_state_flags; TYPE_2__ opt; } ;
struct gc_arena {int dummy; } ;
struct buffer {int dummy; } ;
typedef  int /*<<< orphan*/  sessid ;
typedef  char int64_t ;
typedef  int /*<<< orphan*/  initial_timestamp ;
typedef  int /*<<< orphan*/  hmac_output ;
typedef  int /*<<< orphan*/  hmac_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int AUTH_TOKEN_SESSION_ID_LEN ; 
 int AUTH_TOKEN_VALID_EMPTYUSER ; 
 int /*<<< orphan*/  BLEN (struct buffer*) ; 
 scalar_t__ BPTR (struct buffer*) ; 
 int /*<<< orphan*/  D_SHOW_KEYS ; 
 int /*<<< orphan*/  M_FATAL ; 
 char* SESSION_ID_PREFIX ; 
 struct buffer alloc_buf_gc (int,struct gc_arena*) ; 
 int buf_write (struct buffer*,char*,int) ; 
 int buf_write_u8 (struct buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmsg (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 int /*<<< orphan*/  hmac_ctx_final (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hmac_ctx_reset (int /*<<< orphan*/ *) ; 
 int hmac_ctx_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hmac_ctx_update (int /*<<< orphan*/ *,char const*,int) ; 
 char htonll (char) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ now ; 
 int openvpn_base64_decode (char*,char*,int) ; 
 int /*<<< orphan*/  openvpn_base64_encode (scalar_t__,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  rand_bytes (char*,int) ; 
 char* strdup (char*) ; 
 int strlen (char*) ; 

void
generate_auth_token(const struct user_pass *up, struct tls_multi *multi)
{
    struct gc_arena gc = gc_new();

    int64_t timestamp = htonll((uint64_t)now);
    int64_t initial_timestamp = timestamp;

    hmac_ctx_t *ctx = multi->opt.auth_token_key.hmac;
    ASSERT(hmac_ctx_size(ctx) == 256/8);

    uint8_t sessid[AUTH_TOKEN_SESSION_ID_LEN];

    if (multi->auth_token)
    {
        /* Just enough space to fit 8 bytes+ 1 extra to decode a non padded
         * base64 string (multiple of 3 bytes). 9 bytes => 12 bytes base64
         * bytes
         */
        char old_tstamp_decode[9];

        /*
         * reuse the same session id and timestamp and null terminate it at
         * for base64 decode it only decodes the session id part of it
         */
        char *old_sessid = multi->auth_token + strlen(SESSION_ID_PREFIX);
        char *old_tsamp_initial = old_sessid + AUTH_TOKEN_SESSION_ID_LEN*8/6;

        old_tsamp_initial[12] = '\0';
        ASSERT(openvpn_base64_decode(old_tsamp_initial, old_tstamp_decode, 9) == 9);

        /*
         * Avoid old gcc (4.8.x) complaining about strict aliasing
         * by using a temporary variable instead of doing it in one
         * line
         */
        uint64_t *tstamp_ptr = (uint64_t *) old_tstamp_decode;
        initial_timestamp = *tstamp_ptr;

        old_tsamp_initial[0] = '\0';
        ASSERT(openvpn_base64_decode(old_sessid, sessid, AUTH_TOKEN_SESSION_ID_LEN)==AUTH_TOKEN_SESSION_ID_LEN);


        /* free the auth-token, we will replace it with a new one */
        free(multi->auth_token);
    }
    else if (!rand_bytes(sessid, AUTH_TOKEN_SESSION_ID_LEN))
    {
        msg( M_FATAL, "Failed to get enough randomness for "
             "authentication token");
    }

    /* Calculate the HMAC */
    /* We enforce up->username to be \0 terminated in ssl.c.. Allowing username
     * with \0 in them is asking for troubles in so many ways anyway that we
     * ignore that corner case here
     */
    uint8_t hmac_output[256/8];

    hmac_ctx_reset(ctx);

    /*
     * If the token was only valid for the empty user, also generate
     * a new token with the empty username since we do not want to loose
     * the information that the username cannot be trusted
     */
    if (multi->auth_token_state_flags & AUTH_TOKEN_VALID_EMPTYUSER)
    {
        hmac_ctx_update(ctx, (const uint8_t *) "", 0);
    }
    else
    {
        hmac_ctx_update(ctx, (uint8_t *) up->username, (int) strlen(up->username));
    }
    hmac_ctx_update(ctx, sessid, AUTH_TOKEN_SESSION_ID_LEN);
    hmac_ctx_update(ctx, (uint8_t *) &initial_timestamp, sizeof(initial_timestamp));
    hmac_ctx_update(ctx, (uint8_t *) &timestamp, sizeof(timestamp));
    hmac_ctx_final(ctx, hmac_output);

    /* Construct the unencoded session token */
    struct buffer token = alloc_buf_gc(
        2*sizeof(uint64_t) + AUTH_TOKEN_SESSION_ID_LEN + 256/8, &gc);

    ASSERT(buf_write(&token, sessid, sizeof(sessid)));
    ASSERT(buf_write(&token, &initial_timestamp, sizeof(initial_timestamp)));
    ASSERT(buf_write(&token, &timestamp, sizeof(timestamp)));
    ASSERT(buf_write(&token, hmac_output, sizeof(hmac_output)));

    char *b64output;
    openvpn_base64_encode(BPTR(&token), BLEN(&token), &b64output);

    struct buffer session_token = alloc_buf_gc(
        strlen(SESSION_ID_PREFIX) + strlen(b64output) + 1, &gc);

    ASSERT(buf_write(&session_token, SESSION_ID_PREFIX, strlen(SESSION_ID_PREFIX)));
    ASSERT(buf_write(&session_token, b64output, (int)strlen(b64output)));
    ASSERT(buf_write_u8(&session_token, 0));

    free(b64output);

    multi->auth_token = strdup((char *)BPTR(&session_token));

    dmsg(D_SHOW_KEYS, "Generated token for client: %s (%s)",
         multi->auth_token, up->username);

    gc_free(&gc);
}