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
struct serializer {int (* seek ) (int /*<<< orphan*/ ,int,int) ;int /*<<< orphan*/  data; } ;
typedef  int int64_t ;
typedef  enum serialize_seek_type { ____Placeholder_serialize_seek_type } serialize_seek_type ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline int64_t serializer_seek(struct serializer *s, int64_t offset,
				      enum serialize_seek_type seek_type)
{
	if (s && s->seek)
		return s->seek(s->data, offset, seek_type);
	return -1;
}