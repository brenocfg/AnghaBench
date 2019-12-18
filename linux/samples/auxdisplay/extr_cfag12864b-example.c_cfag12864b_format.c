#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  CFAG12864B_BIT (unsigned char) ; 
 unsigned char CFAG12864B_BPB ; 
 unsigned char CFAG12864B_HEIGHT ; 
 unsigned char CFAG12864B_WIDTH ; 
 int /*<<< orphan*/ * cfag12864b_buffer ; 

__attribute__((used)) static void cfag12864b_format(unsigned char * matrix)
{
	unsigned char i, j, n;

	for (i = 0; i < CFAG12864B_HEIGHT; i++)
	for (j = 0; j < CFAG12864B_WIDTH / CFAG12864B_BPB; j++) {
		cfag12864b_buffer[i * CFAG12864B_WIDTH / CFAG12864B_BPB +
			j] = 0;
		for (n = 0; n < CFAG12864B_BPB; n++)
			if (matrix[i * CFAG12864B_WIDTH +
				j * CFAG12864B_BPB + n])
				cfag12864b_buffer[i * CFAG12864B_WIDTH /
					CFAG12864B_BPB + j] |=
					CFAG12864B_BIT(n);
	}
}