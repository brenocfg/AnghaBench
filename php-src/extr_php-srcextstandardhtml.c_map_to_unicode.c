#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__** inner; } ;
typedef  TYPE_2__ enc_to_uni ;
struct TYPE_4__ {unsigned int* uni_cp; } ;

/* Variables and functions */
 size_t ENT_ENC_TO_UNI_STAGE1 (unsigned int) ; 
 size_t ENT_ENC_TO_UNI_STAGE2 (unsigned int) ; 

__attribute__((used)) static inline void map_to_unicode(unsigned code, const enc_to_uni *table, unsigned *res)
{
	/* only single byte encodings are currently supported; assumed code <= 0xFF */
	*res = table->inner[ENT_ENC_TO_UNI_STAGE1(code)]->uni_cp[ENT_ENC_TO_UNI_STAGE2(code)];
}