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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  magic ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  NRO_OFF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fileType (int /*<<< orphan*/ *) ; 
 int r_buf_read_at (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool check_buffer(RBuffer *b) {
	ut8 magic[4];
	if (r_buf_read_at (b, NRO_OFF (magic), magic, sizeof (magic)) == 4) {
		return fileType (magic) != NULL;
	}
	return false;
}