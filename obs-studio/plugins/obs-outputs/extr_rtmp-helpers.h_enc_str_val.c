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
typedef  int /*<<< orphan*/  AVal ;

/* Variables and functions */
 char* AMF_EncodeNamedString (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flv_str (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static inline void enc_str_val(char **enc, char *end, const char *name,
			       const char *val)
{
	AVal s1, s2;
	*enc = AMF_EncodeNamedString(*enc, end, flv_str(&s1, name),
				     flv_str(&s2, val));
}