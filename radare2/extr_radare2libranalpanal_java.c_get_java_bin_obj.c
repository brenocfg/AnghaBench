#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
struct TYPE_8__ {TYPE_5__* bin; } ;
struct TYPE_13__ {TYPE_1__ binb; } ;
struct TYPE_12__ {TYPE_3__* cur; } ;
struct TYPE_11__ {int /*<<< orphan*/  name; } ;
struct TYPE_10__ {TYPE_2__* o; } ;
struct TYPE_9__ {int /*<<< orphan*/ * bin_obj; TYPE_4__* plugin; } ;
typedef  TYPE_4__ RBinPlugin ;
typedef  int /*<<< orphan*/  RBinJavaObj ;
typedef  TYPE_5__ RBin ;
typedef  TYPE_6__ RAnal ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static RBinJavaObj * get_java_bin_obj(RAnal *anal) {
	RBin *b = anal->binb.bin;
	RBinPlugin *plugin = b->cur && b->cur->o ? b->cur->o->plugin : NULL;
	ut8 is_java = (plugin && strcmp (plugin->name, "java") == 0) ? 1 : 0;
	return is_java ? b->cur->o->bin_obj : NULL;
}