#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* next; TYPE_2__* info; } ;
typedef  TYPE_1__ codec_t ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ TIFFCodec ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _TIFFfree (TYPE_1__*) ; 
 TYPE_1__* registeredCODECS ; 

void
TIFFUnRegisterCODEC(TIFFCodec* c)
{
	codec_t* cd;
	codec_t** pcd;

	for (pcd = &registeredCODECS; (cd = *pcd) != NULL; pcd = &cd->next)
		if (cd->info == c) {
			*pcd = cd->next;
			_TIFFfree(cd);
			return;
		}
	TIFFErrorExt(0, "TIFFUnRegisterCODEC",
	    "Cannot remove compression scheme %s; not registered", c->name);
}