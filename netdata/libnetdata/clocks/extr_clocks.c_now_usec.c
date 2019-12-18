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
typedef  int usec_t ;
struct timespec {int tv_nsec; scalar_t__ tv_sec; } ;
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
 int NSEC_PER_SEC ; 
 int NSEC_PER_USEC ; 
 int USEC_PER_SEC ; 
 int clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline usec_t now_usec(clockid_t clk_id) {
    struct timespec ts;
    if(unlikely(clock_gettime(clk_id, &ts) == -1)) {
        error("clock_gettime(%d, &timespec) failed.", clk_id);
        return 0;
    }
    return (usec_t)ts.tv_sec * USEC_PER_SEC + (ts.tv_nsec % NSEC_PER_SEC) / NSEC_PER_USEC;
}