#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int session_id_length; unsigned char const* session_id; } ;
typedef  TYPE_1__ SSL_SESSION ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_F_SSL_SESSION_SET1_ID ; 
 unsigned int SSL_MAX_SSL_SESSION_ID_LENGTH ; 
 int /*<<< orphan*/  SSL_R_SSL_SESSION_ID_TOO_LONG ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char const*,unsigned char const*,unsigned int) ; 

int SSL_SESSION_set1_id(SSL_SESSION *s, const unsigned char *sid,
                        unsigned int sid_len)
{
    if (sid_len > SSL_MAX_SSL_SESSION_ID_LENGTH) {
      SSLerr(SSL_F_SSL_SESSION_SET1_ID,
             SSL_R_SSL_SESSION_ID_TOO_LONG);
      return 0;
    }
    s->session_id_length = sid_len;
    if (sid != s->session_id)
        memcpy(s->session_id, sid, sid_len);
    return 1;
}