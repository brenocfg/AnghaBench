#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ currUser; } ;
typedef  TYPE_1__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  _doSetSessionAuth (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 scalar_t__ pg_strdup (char const*) ; 
 scalar_t__ strcmp (scalar_t__,char const*) ; 

__attribute__((used)) static void
_becomeUser(ArchiveHandle *AH, const char *user)
{
	if (!user)
		user = "";				/* avoid null pointers */

	if (AH->currUser && strcmp(AH->currUser, user) == 0)
		return;					/* no need to do anything */

	_doSetSessionAuth(AH, user);

	/*
	 * NOTE: currUser keeps track of what the imaginary session user in our
	 * script is
	 */
	if (AH->currUser)
		free(AH->currUser);
	AH->currUser = pg_strdup(user);
}