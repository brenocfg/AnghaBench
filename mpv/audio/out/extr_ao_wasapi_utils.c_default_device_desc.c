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
struct enumerator {int /*<<< orphan*/  log; int /*<<< orphan*/  pEnumerator; } ;
struct device_desc {int dummy; } ;
typedef  int /*<<< orphan*/  IMMDevice ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IMMDeviceEnumerator_GetDefaultAudioEndpoint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  MP_ERR (struct enumerator*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAFE_RELEASE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eMultimedia ; 
 int /*<<< orphan*/  eRender ; 
 struct device_desc* get_device_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_HRESULT_to_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct device_desc *default_device_desc(struct enumerator *e)
{
    IMMDevice *pDevice = NULL;
    HRESULT hr = IMMDeviceEnumerator_GetDefaultAudioEndpoint(
        e->pEnumerator, eRender, eMultimedia, &pDevice);
    if (FAILED(hr)) {
        MP_ERR(e, "Error from GetDefaultAudioEndpoint: %s\n",
               mp_HRESULT_to_str(hr));
        return NULL;
    }
    struct device_desc *d = get_device_desc(e->log, pDevice);
    SAFE_RELEASE(pDevice);
    return d;
}