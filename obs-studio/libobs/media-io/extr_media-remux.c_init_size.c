#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_size; int /*<<< orphan*/  member_0; } ;
struct _stat64 {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__* media_remux_job_t ;
struct TYPE_3__ {int /*<<< orphan*/  in_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  _stat64 (char const*,struct _stat64*) ; 
 int /*<<< orphan*/  stat (char const*,struct stat*) ; 

__attribute__((used)) static inline void init_size(media_remux_job_t job, const char *in_filename)
{
#ifdef _MSC_VER
	struct _stat64 st = {0};
	_stat64(in_filename, &st);
#else
	struct stat st = {0};
	stat(in_filename, &st);
#endif
	job->in_size = st.st_size;
}