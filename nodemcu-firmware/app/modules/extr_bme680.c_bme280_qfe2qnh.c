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
typedef  double int32_t ;

/* Variables and functions */
 double bme680_h ; 
 double bme680_hc ; 
 double pow (double,double) ; 

__attribute__((used)) static double bme280_qfe2qnh(int32_t qfe, int32_t h) {
	double hc;
	if (bme680_h == h) {
		hc = bme680_hc;
	} else {
		hc = pow((double)(1.0 - 2.25577e-5 * h), (double)(-5.25588));
		bme680_hc = hc; bme680_h = h;
	}
	double qnh = (double)qfe * hc;
	return qnh;
}