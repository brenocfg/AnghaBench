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
struct udf_fileident_bh {int dummy; } ;
struct long_ad {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct fileIdentDesc {int /*<<< orphan*/  icb; int /*<<< orphan*/  fileCharacteristics; } ;

/* Variables and functions */
 int /*<<< orphan*/  FID_FILE_CHAR_DELETED ; 
 int /*<<< orphan*/  UDF_FLAG_STRICT ; 
 scalar_t__ UDF_QUERY_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int udf_write_fi (struct inode*,struct fileIdentDesc*,struct fileIdentDesc*,struct udf_fileident_bh*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int udf_delete_entry(struct inode *inode, struct fileIdentDesc *fi,
			    struct udf_fileident_bh *fibh,
			    struct fileIdentDesc *cfi)
{
	cfi->fileCharacteristics |= FID_FILE_CHAR_DELETED;

	if (UDF_QUERY_FLAG(inode->i_sb, UDF_FLAG_STRICT))
		memset(&(cfi->icb), 0x00, sizeof(struct long_ad));

	return udf_write_fi(inode, cfi, fi, fibh, NULL, NULL);
}