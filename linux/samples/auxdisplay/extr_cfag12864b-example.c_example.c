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
 int CFAG12864B_HEIGHT ; 
 int CFAG12864B_WIDTH ; 
 unsigned char EXAMPLES ; 
 int /*<<< orphan*/  cfag12864b_clear () ; 
 int /*<<< orphan*/  cfag12864b_fill () ; 
 int /*<<< orphan*/  cfag12864b_format (unsigned char*) ; 
 int /*<<< orphan*/  cfag12864b_not (unsigned short,unsigned short) ; 
 int /*<<< orphan*/  cfag12864b_set (unsigned short,unsigned short) ; 
 int /*<<< orphan*/  cfag12864b_unset (unsigned short,unsigned short) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  puts (char*) ; 

__attribute__((used)) static void example(unsigned char n)
{
	unsigned short i, j;
	unsigned char matrix[CFAG12864B_WIDTH * CFAG12864B_HEIGHT];

	if (n > EXAMPLES)
		return;

	printf("Example %i/%i - ", n, EXAMPLES);

	switch (n) {
	case 1:
		printf("Draw points setting bits");
		cfag12864b_clear();
		for (i = 0; i < CFAG12864B_WIDTH; i += 2)
			for (j = 0; j < CFAG12864B_HEIGHT; j += 2)
				cfag12864b_set(i, j);
		break;

	case 2:
		printf("Clear the LCD");
		cfag12864b_clear();
		break;

	case 3:
		printf("Draw rows formatting a [128*64] matrix");
		memset(matrix, 0, CFAG12864B_WIDTH * CFAG12864B_HEIGHT);
		for (i = 0; i < CFAG12864B_WIDTH; i++)
			for (j = 0; j < CFAG12864B_HEIGHT; j += 2)
				matrix[j * CFAG12864B_WIDTH + i] = 1;
		cfag12864b_format(matrix);
		break;

	case 4:
		printf("Fill the lcd");
		cfag12864b_fill();
		break;

	case 5:
		printf("Draw columns unsetting bits");
		for (i = 0; i < CFAG12864B_WIDTH; i += 2)
			for (j = 0; j < CFAG12864B_HEIGHT; j++)
				cfag12864b_unset(i, j);
		break;

	case 6:
		printf("Do negative not-ing all bits");
		for (i = 0; i < CFAG12864B_WIDTH; i++)
			for (j = 0; j < CFAG12864B_HEIGHT; j ++)
				cfag12864b_not(i, j);
		break;
	}

	puts(" - [Press Enter]");
}