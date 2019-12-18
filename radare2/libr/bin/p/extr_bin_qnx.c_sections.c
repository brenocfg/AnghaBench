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
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  sections; } ;
struct TYPE_6__ {TYPE_1__* o; } ;
struct TYPE_5__ {TYPE_3__* bin_obj; } ;
typedef  int /*<<< orphan*/  RList ;
typedef  TYPE_2__ RBinFile ;
typedef  TYPE_3__ QnxObj ;

/* Variables and functions */
 int /*<<< orphan*/ * r_list_clone (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_return_val_if_fail (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static RList* sections(RBinFile *bf) {
	r_return_val_if_fail (bf && bf->o, NULL);
	QnxObj *qo = bf->o->bin_obj;
	return r_list_clone (qo->sections);
}