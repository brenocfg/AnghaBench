#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ entry; } ;
struct TYPE_5__ {TYPE_1__ map; } ;
struct TYPE_6__ {int /*<<< orphan*/  pos; TYPE_2__ data; } ;
typedef  TYPE_3__ DocRepresentation ;

/* Variables and functions */
 scalar_t__ WEP_GETPOS (int /*<<< orphan*/ ) ; 
 scalar_t__ WEP_GETWEIGHT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
compareDocR(const void *va, const void *vb)
{
	const DocRepresentation *a = (const DocRepresentation *) va;
	const DocRepresentation *b = (const DocRepresentation *) vb;

	if (WEP_GETPOS(a->pos) == WEP_GETPOS(b->pos))
	{
		if (WEP_GETWEIGHT(a->pos) == WEP_GETWEIGHT(b->pos))
		{
			if (a->data.map.entry == b->data.map.entry)
				return 0;

			return (a->data.map.entry > b->data.map.entry) ? 1 : -1;
		}

		return (WEP_GETWEIGHT(a->pos) > WEP_GETWEIGHT(b->pos)) ? 1 : -1;
	}

	return (WEP_GETPOS(a->pos) > WEP_GETPOS(b->pos)) ? 1 : -1;
}