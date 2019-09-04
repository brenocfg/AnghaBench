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
struct sst_runtime_stream {TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int (* power ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 TYPE_2__* sst ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int power_up_sst(struct sst_runtime_stream *stream)
{
	return stream->ops->power(sst->dev, true);
}