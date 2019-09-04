#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {size_t num; TYPE_7__* array; } ;
struct TYPE_14__ {size_t num; TYPE_5__* array; } ;
struct TYPE_12__ {size_t num; TYPE_3__* array; } ;
struct TYPE_10__ {size_t num; TYPE_1__* array; } ;
struct effect_parser {TYPE_8__ samplers; TYPE_6__ funcs; TYPE_4__ structs; TYPE_2__ params; } ;
struct TYPE_15__ {int written; } ;
struct TYPE_13__ {int written; } ;
struct TYPE_11__ {int written; } ;
struct TYPE_9__ {int written; } ;

/* Variables and functions */

__attribute__((used)) static inline void ep_reset_written(struct effect_parser *ep)
{
	size_t i;
	for (i = 0; i <ep->params.num; i++)
		ep->params.array[i].written = false;
	for (i = 0; i <ep->structs.num; i++)
		ep->structs.array[i].written = false;
	for (i = 0; i <ep->funcs.num; i++)
		ep->funcs.array[i].written = false;
	for (i = 0; i <ep->samplers.num; i++)
		ep->samplers.array[i].written = false;
}