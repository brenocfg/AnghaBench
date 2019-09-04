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
struct rlimit {int dummy; } ;

/* Variables and functions */
 scalar_t__ getrlimit (int,struct rlimit*) ; 
 int /*<<< orphan*/  shutdown (int,char*,int) ; 

__attribute__((used)) static inline void getr(int type, struct rlimit *rlim)
{
	if (getrlimit(type, rlim))
		shutdown(6, "getrlimit()", __LINE__ - 1);
}