#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct smb_vol {scalar_t__ sign; int /*<<< orphan*/  sectype; } ;
struct TCP_Server_Info {int /*<<< orphan*/  sign; TYPE_1__* ops; } ;
struct TYPE_2__ {scalar_t__ (* select_sectype ) (struct TCP_Server_Info*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ Unspecified ; 
 scalar_t__ stub1 (struct TCP_Server_Info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
match_security(struct TCP_Server_Info *server, struct smb_vol *vol)
{
	/*
	 * The select_sectype function should either return the vol->sectype
	 * that was specified, or "Unspecified" if that sectype was not
	 * compatible with the given NEGOTIATE request.
	 */
	if (server->ops->select_sectype(server, vol->sectype)
	     == Unspecified)
		return false;

	/*
	 * Now check if signing mode is acceptable. No need to check
	 * global_secflags at this point since if MUST_SIGN is set then
	 * the server->sign had better be too.
	 */
	if (vol->sign && !server->sign)
		return false;

	return true;
}