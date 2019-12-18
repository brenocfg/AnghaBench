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
struct file_output_data {int /*<<< orphan*/  file; } ;
typedef  int int64_t ;
typedef  enum serialize_seek_type { ____Placeholder_serialize_seek_type } serialize_seek_type ;

/* Variables and functions */
 int SEEK_CUR ; 
 int SEEK_END ; 
 int SEEK_SET ; 
#define  SERIALIZE_SEEK_CURRENT 130 
#define  SERIALIZE_SEEK_END 129 
#define  SERIALIZE_SEEK_START 128 
 int os_fseeki64 (int /*<<< orphan*/ ,int,int) ; 
 int os_ftelli64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int64_t file_output_seek(void *sdata, int64_t offset,
				enum serialize_seek_type seek_type)
{
	struct file_output_data *out = sdata;
	int origin = SEEK_SET;

	switch (seek_type) {
	case SERIALIZE_SEEK_START:
		origin = SEEK_SET;
		break;
	case SERIALIZE_SEEK_CURRENT:
		origin = SEEK_CUR;
		break;
	case SERIALIZE_SEEK_END:
		origin = SEEK_END;
		break;
	}

	if (os_fseeki64(out->file, offset, origin) == -1)
		return -1;

	return os_ftelli64(out->file);
}