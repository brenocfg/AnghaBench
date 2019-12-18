#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct enumerator {long long count; } ;
struct device_desc {int /*<<< orphan*/  name; int /*<<< orphan*/  id; } ;
struct ao {int /*<<< orphan*/  log; } ;
struct TYPE_8__ {int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ bstr ;
typedef  long long UINT ;
typedef  int /*<<< orphan*/ * LPWSTR ;

/* Variables and functions */
 long long BSTR_P (TYPE_1__) ; 
 int /*<<< orphan*/  MP_DBG (struct ao*,char*,long long) ; 
 int /*<<< orphan*/  MP_ERR (struct ao*,char*,...) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct ao*,char*,...) ; 
 int /*<<< orphan*/  MP_WARN (struct ao*,char*,long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAFE_DESTROY (struct device_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bstr0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bstr_eatstart0 (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  bstr_strip (int /*<<< orphan*/ ) ; 
 scalar_t__ bstrcmp (TYPE_1__,int /*<<< orphan*/ ) ; 
 long long bstrtoll (TYPE_1__,TYPE_1__*,int) ; 
 struct enumerator* create_enumerator (int /*<<< orphan*/ ) ; 
 struct device_desc* default_device_desc (struct enumerator*) ; 
 int /*<<< orphan*/  destroy_enumerator (struct enumerator*) ; 
 struct device_desc* device_desc_for_num (struct enumerator*,long long) ; 
 int /*<<< orphan*/ * select_device (int /*<<< orphan*/ ,struct device_desc*) ; 
 int /*<<< orphan*/  talloc_free (struct device_desc*) ; 
 TYPE_1__ wasapi_get_specified_device_string (struct ao*) ; 

LPWSTR wasapi_find_deviceID(struct ao *ao)
{
    LPWSTR deviceID = NULL;
    bstr device = wasapi_get_specified_device_string(ao);
    MP_DBG(ao, "Find device \'%.*s\'\n", BSTR_P(device));

    struct device_desc *d = NULL;
    struct enumerator *enumerator = create_enumerator(ao->log);
    if (!enumerator)
        goto exit_label;

    if (!enumerator->count) {
        MP_ERR(ao, "There are no playback devices available\n");
        goto exit_label;
    }

    if (!device.len) {
        MP_VERBOSE(ao, "No device specified. Selecting default.\n");
        d = default_device_desc(enumerator);
        deviceID = select_device(ao->log, d);
        goto exit_label;
    }

    // try selecting by number
    bstr rest;
    long long devno = bstrtoll(device, &rest, 10);
    if (!rest.len && 0 <= devno && devno < (long long)enumerator->count) {
        MP_VERBOSE(ao, "Selecting device by number: #%lld\n", devno);
        d = device_desc_for_num(enumerator, devno);
        deviceID = select_device(ao->log, d);
        goto exit_label;
    }

    // select by id or name
    bstr_eatstart0(&device, "{0.0.0.00000000}.");
    for (UINT i = 0; i < enumerator->count; i++) {
        d = device_desc_for_num(enumerator, i);
        if (!d)
            goto exit_label;

        if (bstrcmp(device, bstr_strip(bstr0(d->id))) == 0) {
            MP_VERBOSE(ao, "Selecting device by id: \'%.*s\'\n", BSTR_P(device));
            deviceID = select_device(ao->log, d);
            goto exit_label;
        }

        if (bstrcmp(device, bstr_strip(bstr0(d->name))) == 0) {
            if (!deviceID) {
                MP_VERBOSE(ao, "Selecting device by name: \'%.*s\'\n", BSTR_P(device));
                deviceID = select_device(ao->log, d);
            } else {
                MP_WARN(ao, "Multiple devices matched \'%.*s\'."
                        "Ignoring device \'%s\' (%s).\n",
                        BSTR_P(device), d->id, d->name);
            }
        }
        SAFE_DESTROY(d, talloc_free(d));
    }

    if (!deviceID)
        MP_ERR(ao, "Failed to find device \'%.*s\'\n", BSTR_P(device));

exit_label:
    talloc_free(d);
    destroy_enumerator(enumerator);
    return deviceID;
}