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
typedef  TYPE_1__* gdRectPtr ;
struct TYPE_3__ {int x; int y; int width; int height; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char const*,int,int,int,int) ; 

void gdDumpRect(const char *msg, gdRectPtr r)
{
	printf("%s (%i, %i) (%i, %i)\n", msg, r->x, r->y, r->width, r->height);
}