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
typedef  int ut8 ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  CGCMAG ; 
 int SCGCMAG ; 
 int /*<<< orphan*/  memcmp (int*,int /*<<< orphan*/ ,int) ; 
 int r_buf_read_at (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static bool check_buffer(RBuffer *buf) {
	ut8 tmp[SCGCMAG + 1];
	int r = r_buf_read_at (buf, 0, tmp, sizeof (tmp));
	return r > SCGCMAG && !memcmp (tmp, CGCMAG, SCGCMAG) && tmp[4] != 2;
}