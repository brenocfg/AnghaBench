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
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  DOWNGRADE ;

/* Variables and functions */
 int /*<<< orphan*/  DOWNGRADE_NONE ; 
 int /*<<< orphan*/  DOWNGRADE_TO_1_1 ; 
 int /*<<< orphan*/  DOWNGRADE_TO_1_2 ; 
 int /*<<< orphan*/  SSL_IS_DTLS (int /*<<< orphan*/ *) ; 
 int TLS1_2_VERSION ; 
 int TLS1_3_VERSION ; 
 scalar_t__ ssl_version_supported (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void check_for_downgrade(SSL *s, int vers, DOWNGRADE *dgrd)
{
    if (vers == TLS1_2_VERSION
            && ssl_version_supported(s, TLS1_3_VERSION, NULL)) {
        *dgrd = DOWNGRADE_TO_1_2;
    } else if (!SSL_IS_DTLS(s)
            && vers < TLS1_2_VERSION
               /*
                * We need to ensure that a server that disables TLSv1.2
                * (creating a hole between TLSv1.3 and TLSv1.1) can still
                * complete handshakes with clients that support TLSv1.2 and
                * below. Therefore we do not enable the sentinel if TLSv1.3 is
                * enabled and TLSv1.2 is not.
                */
            && ssl_version_supported(s, TLS1_2_VERSION, NULL)) {
        *dgrd = DOWNGRADE_TO_1_1;
    } else {
        *dgrd = DOWNGRADE_NONE;
    }
}