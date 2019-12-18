#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  ctx_j; } ;

/* Variables and functions */
 int /*<<< orphan*/  json_append_member (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_mkstring (char const*) ; 
 TYPE_1__ s ; 

__attribute__((used)) static void cloudlog_bind_locked(const char* k, const char* v) {
  json_append_member(s.ctx_j, k, json_mkstring(v));
}