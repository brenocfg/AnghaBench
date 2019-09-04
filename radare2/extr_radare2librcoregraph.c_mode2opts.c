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
typedef  int /*<<< orphan*/  RAGraph ;

/* Variables and functions */
 int BODY_COMMENTS ; 
 int BODY_OFFSETS ; 
 int BODY_SUMMARY ; 
 scalar_t__ is_comments (int /*<<< orphan*/  const*) ; 
 scalar_t__ is_offset (int /*<<< orphan*/  const*) ; 
 scalar_t__ is_summary (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int mode2opts(const RAGraph *g) {
	int opts = 0;
	if (is_offset (g)) {
		opts |= BODY_OFFSETS;
	}
	if (is_comments (g)) {
		opts |= BODY_COMMENTS;
	}
	if (is_summary (g)) {
		opts |= BODY_SUMMARY;
	}
	return opts;
}