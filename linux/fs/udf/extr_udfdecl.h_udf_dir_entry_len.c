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
struct fileIdentDesc {scalar_t__ lengthFileIdent; int /*<<< orphan*/  lengthOfImpUse; } ;

/* Variables and functions */
 unsigned int ALIGN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UDF_NAME_PAD ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int udf_dir_entry_len(struct fileIdentDesc *cfi)
{
	return ALIGN(sizeof(struct fileIdentDesc) +
		le16_to_cpu(cfi->lengthOfImpUse) + cfi->lengthFileIdent,
		UDF_NAME_PAD);
}