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
struct TYPE_3__ {int /*<<< orphan*/  (* get_index ) (TYPE_1__*) ;} ;

/* Variables and functions */
 scalar_t__ index_count ; 
 int sentence_count ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 TYPE_1__* synth ; 

void spk_reset_index_count(int sc)
{
	static int first = 1;

	if (first)
		first = 0;
	else
		synth->get_index(synth);
	index_count = 0;
	sentence_count = sc;
}