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
typedef  int /*<<< orphan*/  remoteConnHashEnt ;
struct TYPE_3__ {int entrysize; int /*<<< orphan*/  keysize; } ;
typedef  int /*<<< orphan*/  HTAB ;
typedef  TYPE_1__ HASHCTL ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_ELEM ; 
 int /*<<< orphan*/  NAMEDATALEN ; 
 int /*<<< orphan*/  NUMCONN ; 
 int /*<<< orphan*/ * hash_create (char*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HTAB *
createConnHash(void)
{
	HASHCTL		ctl;

	ctl.keysize = NAMEDATALEN;
	ctl.entrysize = sizeof(remoteConnHashEnt);

	return hash_create("Remote Con hash", NUMCONN, &ctl, HASH_ELEM);
}