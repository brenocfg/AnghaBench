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
typedef  int const mode_t ;

/* Variables and functions */
 int S_IRGRP ; 
 int S_IROTH ; 
 int S_IRUSR ; 

__attribute__((used)) static bool is_world_readable(mode_t mode)
{
    const mode_t world_readable = S_IRUSR | S_IRGRP | S_IROTH;

    return (mode & world_readable) == world_readable;
}