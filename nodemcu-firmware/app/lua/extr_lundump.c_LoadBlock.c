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
struct TYPE_3__ {size_t total; int /*<<< orphan*/  Z; } ;
typedef  TYPE_1__ LoadState ;

/* Variables and functions */
 int /*<<< orphan*/  IF (int,char*) ; 
 size_t luaZ_read (int /*<<< orphan*/ ,void*,size_t) ; 

__attribute__((used)) static void LoadBlock(LoadState* S, void* b, size_t size)
{
 size_t r=luaZ_read(S->Z,b,size);
 IF (r!=0, "unexpected end");
 S->total+=size;
}