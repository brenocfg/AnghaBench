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

/* Variables and functions */
#define  SK_DROP 129 
#define  SK_PASS 128 
 int __SK_DROP ; 
 int __SK_PASS ; 
 int __SK_REDIRECT ; 

__attribute__((used)) static int sk_psock_map_verd(int verdict, bool redir)
{
	switch (verdict) {
	case SK_PASS:
		return redir ? __SK_REDIRECT : __SK_PASS;
	case SK_DROP:
	default:
		break;
	}

	return __SK_DROP;
}