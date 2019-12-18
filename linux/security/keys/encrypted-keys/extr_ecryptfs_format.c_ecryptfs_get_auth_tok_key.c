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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int /*<<< orphan*/ * session_key_encryption_key; } ;
struct TYPE_4__ {TYPE_1__ password; } ;
struct ecryptfs_auth_tok {TYPE_2__ token; } ;

/* Variables and functions */

u8 *ecryptfs_get_auth_tok_key(struct ecryptfs_auth_tok *auth_tok)
{
	return auth_tok->token.password.session_key_encryption_key;
}