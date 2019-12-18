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
typedef  scalar_t__ NVENCSTATUS ;

/* Variables and functions */
 scalar_t__ NV_ENC_SUCCESS ; 
 int /*<<< orphan*/  error (char*,char const*,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_error_name (scalar_t__) ; 

__attribute__((used)) static inline bool nv_failed(NVENCSTATUS err, const char *func,
			     const char *call)
{
	if (err == NV_ENC_SUCCESS)
		return false;

	error("%s: %s failed: %d (%s)", func, call, (int)err,
	      nv_error_name(err));
	return true;
}