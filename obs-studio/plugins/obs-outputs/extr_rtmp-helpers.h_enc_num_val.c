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
 char* AMF_EncodeNamedNumber (char*,char*,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  flv_str (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static inline void enc_num_val(char **enc, char *end, const char *name,
			       double val)
{
	AVal s;
	*enc = AMF_EncodeNamedNumber(*enc, end, flv_str(&s, name), val);
}