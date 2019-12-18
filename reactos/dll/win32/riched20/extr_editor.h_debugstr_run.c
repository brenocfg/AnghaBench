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
struct TYPE_4__ {int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ ME_Run ;

/* Variables and functions */
 char const* debugstr_wn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_text (TYPE_1__ const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline const char *debugstr_run( const ME_Run *run )
{
    return debugstr_wn( get_text( run, 0 ), run->len );
}