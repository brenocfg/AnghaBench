#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_5__ {int /*<<< orphan*/  next; int /*<<< orphan*/  priv; TYPE_1__* op; } ;
struct TYPE_4__ {int (* push ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ;} ;
typedef  TYPE_2__ PushFilter ;

/* Variables and functions */
 int PXE_BUG ; 
 int pushf_write (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int
wrap_process(PushFilter *mp, const uint8 *data, int len)
{
	int			res;

	if (mp->op->push != NULL)
		res = mp->op->push(mp->next, mp->priv, data, len);
	else
		res = pushf_write(mp->next, data, len);
	if (res > 0)
		return PXE_BUG;
	return res;
}