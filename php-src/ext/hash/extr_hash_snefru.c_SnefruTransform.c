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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {unsigned int* state; } ;
typedef  TYPE_1__ PHP_SNEFRU_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  Snefru (unsigned int*) ; 
 int /*<<< orphan*/  ZEND_SECURE_ZERO (unsigned int*,int) ; 

__attribute__((used)) static inline void SnefruTransform(PHP_SNEFRU_CTX *context, const unsigned char input[32])
{
	int i, j;

	for (i = 0, j = 0; i < 32; i += 4, ++j) {
		context->state[8+j] =	((unsigned)input[i] << 24) | ((unsigned)input[i+1] << 16) |
								((unsigned)input[i+2] << 8) | (unsigned)input[i+3];
	}
	Snefru(context->state);
	ZEND_SECURE_ZERO(&context->state[8], sizeof(uint32_t) * 8);
}