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
struct mxser_board {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ mxser_overlapping_vector (struct mxser_board*) ; 
 scalar_t__ request_region (int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static int mxser_request_vector(struct mxser_board *brd)
{
	if (mxser_overlapping_vector(brd))
		return 0;
	return request_region(brd->vector, 1, "mxser(vector)") ? 0 : -EIO;
}