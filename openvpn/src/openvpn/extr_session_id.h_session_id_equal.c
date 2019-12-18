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
struct session_id {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  SID_SIZE ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
session_id_equal(const struct session_id *sid1,
                 const struct session_id *sid2)
{
    return !memcmp(sid1->id, sid2->id, SID_SIZE);
}