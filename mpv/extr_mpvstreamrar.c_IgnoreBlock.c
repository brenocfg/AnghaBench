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
struct stream {int dummy; } ;
struct TYPE_4__ {int type; } ;
typedef  TYPE_1__ rar_block_t ;

/* Variables and functions */
 scalar_t__ PeekBlock (struct stream*,TYPE_1__*) ; 
 int SkipBlock (struct stream*,TYPE_1__*) ; 

__attribute__((used)) static int IgnoreBlock(struct stream *s, int block)
{
    /* */
    rar_block_t bk;
    if (PeekBlock(s, &bk) || bk.type != block)
        return -1;
    return SkipBlock(s, &bk);
}