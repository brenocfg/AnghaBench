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
typedef  int /*<<< orphan*/  multipart_buffer ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int FILLUNIT ; 
 char* erealloc (char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int multipart_buffer_read (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *multipart_buffer_read_body(multipart_buffer *self, size_t *len)
{
	char buf[FILLUNIT], *out=NULL;
	int total_bytes=0, read_bytes=0;

	while((read_bytes = multipart_buffer_read(self, buf, sizeof(buf), NULL))) {
		out = erealloc(out, total_bytes + read_bytes + 1);
		memcpy(out + total_bytes, buf, read_bytes);
		total_bytes += read_bytes;
	}

	if (out) {
		out[total_bytes] = '\0';
	}
	*len = total_bytes;

	return out;
}