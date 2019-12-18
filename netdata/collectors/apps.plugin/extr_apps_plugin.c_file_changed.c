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
struct timespec {scalar_t__ tv_sec; scalar_t__ tv_nsec; } ;
struct TYPE_2__ {scalar_t__ tv_sec; scalar_t__ tv_nsec; } ;
struct stat {TYPE_1__ st_mtim; } ;

/* Variables and functions */
 scalar_t__ likely (int) ; 

int file_changed(const struct stat *statbuf, struct timespec *last_modification_time) {
    if(likely(statbuf->st_mtim.tv_sec == last_modification_time->tv_sec &&
       statbuf->st_mtim.tv_nsec == last_modification_time->tv_nsec)) return 0;

    last_modification_time->tv_sec = statbuf->st_mtim.tv_sec;
    last_modification_time->tv_nsec = statbuf->st_mtim.tv_nsec;

    return 1;
}