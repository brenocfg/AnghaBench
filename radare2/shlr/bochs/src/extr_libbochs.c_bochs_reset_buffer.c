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
struct TYPE_3__ {scalar_t__ punteroBuffer; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ libbochs_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIZE_BUF ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bochs_reset_buffer(libbochs_t* b) {
	memset (b->data, 0, SIZE_BUF);
	b->punteroBuffer = 0;
}