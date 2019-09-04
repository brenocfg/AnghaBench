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
struct TYPE_3__ {int /*<<< orphan*/ * abstract; } ;
typedef  TYPE_1__ php_stream ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_HASHTABLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_hash_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int phar_dir_close(php_stream *stream, int close_handle)  /* {{{ */
{
	HashTable *data = (HashTable *)stream->abstract;

	if (data) {
		zend_hash_destroy(data);
		FREE_HASHTABLE(data);
		stream->abstract = NULL;
	}

	return 0;
}