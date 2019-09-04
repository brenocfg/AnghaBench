#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  smart_str ;
typedef  TYPE_2__* encodePtr ;
struct TYPE_4__ {int /*<<< orphan*/  sdl_type; int /*<<< orphan*/  ns; int /*<<< orphan*/  type_str; int /*<<< orphan*/  type; } ;
struct TYPE_5__ {TYPE_1__ details; } ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  WSDL_CACHE_PUT_INT (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdl_serialize_string (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdl_serialize_type_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sdl_serialize_encoder(encodePtr enc, HashTable *tmp_types, smart_str *out)
{
	WSDL_CACHE_PUT_INT(enc->details.type, out);
	sdl_serialize_string(enc->details.type_str, out);
	sdl_serialize_string(enc->details.ns, out);
	sdl_serialize_type_ref(enc->details.sdl_type, tmp_types, out);
}