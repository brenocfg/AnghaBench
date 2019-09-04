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
struct iscsi_conn {struct iscsi_chap* auth_protocol; } ;
struct iscsi_chap {int /*<<< orphan*/  challenge; } ;

/* Variables and functions */
 int CHAP_CHALLENGE_LENGTH ; 
 int /*<<< orphan*/  bin2hex (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int get_random_bytes_wait (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,char*,unsigned char*) ; 
 scalar_t__ sprintf (char*,char*,unsigned char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int chap_gen_challenge(
	struct iscsi_conn *conn,
	int caller,
	char *c_str,
	unsigned int *c_len)
{
	int ret;
	unsigned char challenge_asciihex[CHAP_CHALLENGE_LENGTH * 2 + 1];
	struct iscsi_chap *chap = conn->auth_protocol;

	memset(challenge_asciihex, 0, CHAP_CHALLENGE_LENGTH * 2 + 1);

	ret = get_random_bytes_wait(chap->challenge, CHAP_CHALLENGE_LENGTH);
	if (unlikely(ret))
		return ret;
	bin2hex(challenge_asciihex, chap->challenge,
				CHAP_CHALLENGE_LENGTH);
	/*
	 * Set CHAP_C, and copy the generated challenge into c_str.
	 */
	*c_len += sprintf(c_str + *c_len, "CHAP_C=0x%s", challenge_asciihex);
	*c_len += 1;

	pr_debug("[%s] Sending CHAP_C=0x%s\n\n", (caller) ? "server" : "client",
			challenge_asciihex);
	return 0;
}