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
#define  CRUSH_BUCKET_LIST 132 
#define  CRUSH_BUCKET_STRAW 131 
#define  CRUSH_BUCKET_STRAW2 130 
#define  CRUSH_BUCKET_TREE 129 
#define  CRUSH_BUCKET_UNIFORM 128 

const char *crush_bucket_alg_name(int alg)
{
	switch (alg) {
	case CRUSH_BUCKET_UNIFORM: return "uniform";
	case CRUSH_BUCKET_LIST: return "list";
	case CRUSH_BUCKET_TREE: return "tree";
	case CRUSH_BUCKET_STRAW: return "straw";
	case CRUSH_BUCKET_STRAW2: return "straw2";
	default: return "unknown";
	}
}