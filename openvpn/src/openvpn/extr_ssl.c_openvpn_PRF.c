#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  char uint8_t ;
struct session_id {char const* id; } ;
struct buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BLEN (struct buffer*) ; 
 int /*<<< orphan*/  BPTR (struct buffer*) ; 
 int SID_SIZE ; 
 int /*<<< orphan*/  VALGRIND_MAKE_READABLE (void*,int) ; 
 struct buffer alloc_buf (int) ; 
 int /*<<< orphan*/  buf_clear (struct buffer*) ; 
 int /*<<< orphan*/  buf_write (struct buffer*,char const*,int) ; 
 int /*<<< orphan*/  free_buf (struct buffer*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  tls1_PRF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,char*,int) ; 

__attribute__((used)) static void
openvpn_PRF(const uint8_t *secret,
            int secret_len,
            const char *label,
            const uint8_t *client_seed,
            int client_seed_len,
            const uint8_t *server_seed,
            int server_seed_len,
            const struct session_id *client_sid,
            const struct session_id *server_sid,
            uint8_t *output,
            int output_len)
{
    /* concatenate seed components */

    struct buffer seed = alloc_buf(strlen(label)
                                   + client_seed_len
                                   + server_seed_len
                                   + SID_SIZE * 2);

    ASSERT(buf_write(&seed, label, strlen(label)));
    ASSERT(buf_write(&seed, client_seed, client_seed_len));
    ASSERT(buf_write(&seed, server_seed, server_seed_len));

    if (client_sid)
    {
        ASSERT(buf_write(&seed, client_sid->id, SID_SIZE));
    }
    if (server_sid)
    {
        ASSERT(buf_write(&seed, server_sid->id, SID_SIZE));
    }

    /* compute PRF */
    tls1_PRF(BPTR(&seed), BLEN(&seed), secret, secret_len, output, output_len);

    buf_clear(&seed);
    free_buf(&seed);

    VALGRIND_MAKE_READABLE((void *)output, output_len);
}