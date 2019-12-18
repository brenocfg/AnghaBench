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
typedef  unsigned int UINT ;
struct TYPE_3__ {int style; unsigned int buffer_limit; } ;
typedef  TYPE_1__ EDITSTATE ;

/* Variables and functions */
 int ES_MULTILINE ; 
 unsigned int min (unsigned int,int) ; 

__attribute__((used)) static void EDIT_EM_SetLimitText(EDITSTATE *es, UINT limit)
{
    if (!limit) limit = ~0u;
    if (!(es->style & ES_MULTILINE)) limit = min(limit, 0x7ffffffe);
    es->buffer_limit = limit;
}