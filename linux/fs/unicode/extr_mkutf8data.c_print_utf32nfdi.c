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
struct TYPE_2__ {int /*<<< orphan*/  utf32nfdi; } ;

/* Variables and functions */
 int /*<<< orphan*/  print_utf32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_1__* unicode_data ; 

__attribute__((used)) static void print_utf32nfdi(unsigned int unichar)
{
	printf(" %X ->", unichar);
	print_utf32(unicode_data[unichar].utf32nfdi);
	printf("\n");
}