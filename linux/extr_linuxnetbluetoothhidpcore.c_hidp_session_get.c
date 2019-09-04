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
struct hidp_session {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hidp_session_get(struct hidp_session *session)
{
	kref_get(&session->ref);
}