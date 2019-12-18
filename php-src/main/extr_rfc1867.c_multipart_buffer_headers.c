#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_llist ;
struct TYPE_10__ {int /*<<< orphan*/ * c; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ smart_string ;
struct TYPE_11__ {int /*<<< orphan*/  detect_order_size; int /*<<< orphan*/  detect_order; int /*<<< orphan*/  input_encoding; int /*<<< orphan*/  boundary; } ;
typedef  TYPE_2__ multipart_buffer ;
struct TYPE_12__ {char* key; int /*<<< orphan*/ * value; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ mime_header_entry ;

/* Variables and functions */
 char* estrdup (char*) ; 
 int /*<<< orphan*/  find_boundary (TYPE_2__*,int /*<<< orphan*/ ) ; 
 char* get_line (TYPE_2__*) ; 
 scalar_t__ isspace (char) ; 
 scalar_t__ php_rfc1867_encoding_translation () ; 
 int /*<<< orphan*/  smart_string_0 (TYPE_1__*) ; 
 int /*<<< orphan*/  smart_string_appends (TYPE_1__*,char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  zend_llist_add_element (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  zend_multibyte_encoding_detector (unsigned char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int multipart_buffer_headers(multipart_buffer *self, zend_llist *header)
{
	char *line;
	mime_header_entry entry = {0};
	smart_string buf_value = {0};
	char *key = NULL;

	/* didn't find boundary, abort */
	if (!find_boundary(self, self->boundary)) {
		return 0;
	}

	/* get lines of text, or CRLF_CRLF */

	while ((line = get_line(self)) && line[0] != '\0') {
		/* add header to table */
		char *value = NULL;

		if (php_rfc1867_encoding_translation()) {
			self->input_encoding = zend_multibyte_encoding_detector((const unsigned char *) line, strlen(line), self->detect_order, self->detect_order_size);
		}

		/* space in the beginning means same header */
		if (!isspace(line[0])) {
			value = strchr(line, ':');
		}

		if (value) {
			if (buf_value.c && key) {
				/* new entry, add the old one to the list */
				smart_string_0(&buf_value);
				entry.key = key;
				entry.value = buf_value.c;
				zend_llist_add_element(header, &entry);
				buf_value.c = NULL;
				key = NULL;
			}

			*value = '\0';
			do { value++; } while (isspace(*value));

			key = estrdup(line);
			smart_string_appends(&buf_value, value);
		} else if (buf_value.c) { /* If no ':' on the line, add to previous line */
			smart_string_appends(&buf_value, line);
		} else {
			continue;
		}
	}

	if (buf_value.c && key) {
		/* add the last one to the list */
		smart_string_0(&buf_value);
		entry.key = key;
		entry.value = buf_value.c;
		zend_llist_add_element(header, &entry);
	}

	return 1;
}