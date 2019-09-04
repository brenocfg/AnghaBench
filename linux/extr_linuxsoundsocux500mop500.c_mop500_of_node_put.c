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
struct TYPE_2__ {int /*<<< orphan*/  codec_of_node; int /*<<< orphan*/  cpu_of_node; } ;

/* Variables and functions */
 TYPE_1__* mop500_dai_links ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mop500_of_node_put(void)
{
	int i;

	for (i = 0; i < 2; i++) {
		of_node_put(mop500_dai_links[i].cpu_of_node);
		of_node_put(mop500_dai_links[i].codec_of_node);
	}
}