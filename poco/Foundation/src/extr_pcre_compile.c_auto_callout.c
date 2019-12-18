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
typedef  int /*<<< orphan*/  pcre_uchar ;
struct TYPE_3__ {int /*<<< orphan*/  const* start_pattern; } ;
typedef  TYPE_1__ compile_data ;

/* Variables and functions */
 int LINK_SIZE ; 
 int /*<<< orphan*/  OP_CALLOUT ; 
 int /*<<< orphan*/  PUT (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static pcre_uchar *
auto_callout(pcre_uchar *code, const pcre_uchar *ptr, compile_data *cd)
{
*code++ = OP_CALLOUT;
*code++ = 255;
PUT(code, 0, (int)(ptr - cd->start_pattern));  /* Pattern offset */
PUT(code, LINK_SIZE, 0);                       /* Default length */
return code + 2 * LINK_SIZE;
}