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
typedef  scalar_t__ zend_off_t ;
struct TYPE_3__ {scalar_t__ abstract; } ;
typedef  TYPE_1__ php_stream ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int SEEK_END ; 
 int SEEK_SET ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  zend_hash_internal_pointer_reset (int /*<<< orphan*/ *) ; 
 scalar_t__ zend_hash_move_forward (int /*<<< orphan*/ *) ; 
 scalar_t__ zend_hash_num_elements (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int phar_dir_seek(php_stream *stream, zend_off_t offset, int whence, zend_off_t *newoffset) /* {{{ */
{
	HashTable *data = (HashTable *)stream->abstract;

	if (!data) {
		return -1;
	}

	if (whence == SEEK_END) {
		whence = SEEK_SET;
		offset = zend_hash_num_elements(data) + offset;
	}

	if (whence == SEEK_SET) {
		zend_hash_internal_pointer_reset(data);
	}

	if (offset < 0) {
		return -1;
	} else {
		*newoffset = 0;
		while (*newoffset < offset && zend_hash_move_forward(data) == SUCCESS) {
			++(*newoffset);
		}
		return 0;
	}
}