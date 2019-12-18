#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int* state; } ;
typedef  TYPE_1__ PHP_GOST_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  Gost (TYPE_1__*,int*) ; 

__attribute__((used)) static inline void GostTransform(PHP_GOST_CTX *context, const unsigned char input[32])
{
	int i, j;
	uint32_t data[8], temp = 0;

	for (i = 0, j = 0; i < 8; ++i, j += 4) {
		data[i] =	((uint32_t) input[j]) | (((uint32_t) input[j + 1]) << 8) |
					(((uint32_t) input[j + 2]) << 16) | (((uint32_t) input[j + 3]) << 24);
		context->state[i + 8] += data[i] + temp;
		temp = context->state[i + 8] < data[i] ? 1 : (context->state[i + 8] == data[i] ? temp : 0);
	}

	Gost(context, data);
}