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
typedef  int /*<<< orphan*/  RDebug ;

/* Variables and functions */

__attribute__((used)) static char *r_debug_native_reg_profile(RDebug *dbg) {
#if __WINDOWS__
/*_______
 |   |   |
 |___|___|
 |   |   |
 |___|___|
*/
	if (dbg->bits & R_SYS_BITS_64) {
#include "reg/windows-x64.h"
	} else {
#include "reg/windows-x86.h"
	}
#elif (__OpenBSD__ || __NetBSD__)
/*                           __.--..__
       \-/-/-/    _ __  _.--'  _.--'
  _  \'       \   \\  ''      `------.__
  \\/      __)_)   \\      ____..---'
  //\       o  o    \\----'
     / <_/      3    \\
      \_,_,__,_/      \\
*/
#if __i386__
#include "reg/netbsd-x86.h"
#elif __x86_64__
#include "reg/netbsd-x64.h"
#else
#error "Unsupported BSD architecture"
#endif

#elif __KFBSD__ || __FreeBSD__
/*
    /(       ).
    \ \__   /|
    /  _ '-/ |
   (/\/ |    \
   / /  | \   )
   O O _/     |
  (__)  __   /
    \___/   /
      `----'
*/
#if __i386__ || __i386
#include "reg/kfbsd-x86.h"
#elif __x86_64__ || __amd64__
#include "reg/kfbsd-x64.h"
#elif __aarch64__
#include "reg/kfbsd-arm64.h"
#else
#error "Unsupported BSD architecture"
#endif

#else
#warning Unsupported Kernel
	return NULL;
#endif
}