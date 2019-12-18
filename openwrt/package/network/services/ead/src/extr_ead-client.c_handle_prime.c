#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ead_msg_salt {int len; int /*<<< orphan*/  prime; int /*<<< orphan*/  ext_salt; int /*<<< orphan*/  salt; } ;
struct TYPE_7__ {int len; scalar_t__* data; } ;
struct TYPE_6__ {int /*<<< orphan*/  generator; int /*<<< orphan*/  modulus; } ;

/* Variables and functions */
 scalar_t__ EAD_AUTH_MD5 ; 
 struct ead_msg_salt* EAD_DATA (int /*<<< orphan*/ ,TYPE_3__) ; 
 int MAXSALTLEN ; 
 scalar_t__ auth_type ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg ; 
 scalar_t__* pw_salt ; 
 TYPE_3__ salt ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  t_clientopen (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*) ; 
 TYPE_1__* t_getpreparam (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tc ; 
 TYPE_1__* tcp ; 
 int /*<<< orphan*/  username ; 

__attribute__((used)) static bool
handle_prime(void)
{
	struct ead_msg_salt *sb = EAD_DATA(msg, salt);

	salt.len = sb->len;
	memcpy(salt.data, sb->salt, salt.len);

	if (auth_type == EAD_AUTH_MD5) {
		memcpy(pw_salt, sb->ext_salt, MAXSALTLEN);
		pw_salt[MAXSALTLEN - 1] = 0;
	}

	tcp = t_getpreparam(sb->prime);
	tc = t_clientopen(username, &tcp->modulus, &tcp->generator, &salt);
	if (!tc) {
		fprintf(stderr, "Client open failed\n");
		return false;
	}

	return true;
}