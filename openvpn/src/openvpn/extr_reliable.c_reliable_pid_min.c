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
typedef  int /*<<< orphan*/  packet_id_type ;

/* Variables and functions */
 int /*<<< orphan*/  reliable_pid_in_range1 (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int) ; 

__attribute__((used)) static inline bool
reliable_pid_min(const packet_id_type p1,
                 const packet_id_type p2)
{
    return !reliable_pid_in_range1(p1, p2, 0x80000000u);
}