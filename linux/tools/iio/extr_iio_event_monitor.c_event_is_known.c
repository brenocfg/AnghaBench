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
struct iio_event_data {int /*<<< orphan*/  id; } ;
typedef  enum iio_modifier { ____Placeholder_iio_modifier } iio_modifier ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;
typedef  enum iio_chan_type { ____Placeholder_iio_chan_type } iio_chan_type ;

/* Variables and functions */
#define  IIO_ACCEL 213 
#define  IIO_ACTIVITY 212 
#define  IIO_ALTVOLTAGE 211 
#define  IIO_ANGL 210 
#define  IIO_ANGL_VEL 209 
#define  IIO_CAPACITANCE 208 
#define  IIO_CCT 207 
#define  IIO_CONCENTRATION 206 
#define  IIO_CURRENT 205 
#define  IIO_DISTANCE 204 
#define  IIO_ENERGY 203 
 int IIO_EVENT_CODE_EXTRACT_CHAN_TYPE (int /*<<< orphan*/ ) ; 
 int IIO_EVENT_CODE_EXTRACT_DIR (int /*<<< orphan*/ ) ; 
 int IIO_EVENT_CODE_EXTRACT_MODIFIER (int /*<<< orphan*/ ) ; 
 int IIO_EVENT_CODE_EXTRACT_TYPE (int /*<<< orphan*/ ) ; 
#define  IIO_EV_DIR_EITHER 202 
#define  IIO_EV_DIR_FALLING 201 
#define  IIO_EV_DIR_NONE 200 
#define  IIO_EV_DIR_RISING 199 
#define  IIO_EV_TYPE_CHANGE 198 
#define  IIO_EV_TYPE_MAG 197 
#define  IIO_EV_TYPE_MAG_ADAPTIVE 196 
#define  IIO_EV_TYPE_ROC 195 
#define  IIO_EV_TYPE_THRESH 194 
#define  IIO_EV_TYPE_THRESH_ADAPTIVE 193 
#define  IIO_GRAVITY 192 
#define  IIO_HUMIDITYRELATIVE 191 
#define  IIO_INCLI 190 
#define  IIO_INTENSITY 189 
#define  IIO_LIGHT 188 
#define  IIO_MAGN 187 
#define  IIO_MASSCONCENTRATION 186 
#define  IIO_MOD_CO2 185 
#define  IIO_MOD_ETHANOL 184 
#define  IIO_MOD_H2 183 
#define  IIO_MOD_I 182 
#define  IIO_MOD_JOGGING 181 
#define  IIO_MOD_LIGHT_BLUE 180 
#define  IIO_MOD_LIGHT_BOTH 179 
#define  IIO_MOD_LIGHT_CLEAR 178 
#define  IIO_MOD_LIGHT_DUV 177 
#define  IIO_MOD_LIGHT_GREEN 176 
#define  IIO_MOD_LIGHT_IR 175 
#define  IIO_MOD_LIGHT_RED 174 
#define  IIO_MOD_LIGHT_UV 173 
#define  IIO_MOD_NORTH_MAGN 172 
#define  IIO_MOD_NORTH_MAGN_TILT_COMP 171 
#define  IIO_MOD_NORTH_TRUE 170 
#define  IIO_MOD_NORTH_TRUE_TILT_COMP 169 
#define  IIO_MOD_PM1 168 
#define  IIO_MOD_PM10 167 
#define  IIO_MOD_PM2P5 166 
#define  IIO_MOD_PM4 165 
#define  IIO_MOD_Q 164 
#define  IIO_MOD_QUATERNION 163 
#define  IIO_MOD_ROOT_SUM_SQUARED_X_Y 162 
#define  IIO_MOD_ROOT_SUM_SQUARED_X_Y_Z 161 
#define  IIO_MOD_RUNNING 160 
#define  IIO_MOD_STILL 159 
#define  IIO_MOD_SUM_SQUARED_X_Y_Z 158 
#define  IIO_MOD_TEMP_AMBIENT 157 
#define  IIO_MOD_TEMP_OBJECT 156 
#define  IIO_MOD_VOC 155 
#define  IIO_MOD_WALKING 154 
#define  IIO_MOD_X 153 
#define  IIO_MOD_X_AND_Y 152 
#define  IIO_MOD_X_AND_Y_AND_Z 151 
#define  IIO_MOD_X_AND_Z 150 
#define  IIO_MOD_X_OR_Y 149 
#define  IIO_MOD_X_OR_Y_OR_Z 148 
#define  IIO_MOD_X_OR_Z 147 
#define  IIO_MOD_Y 146 
#define  IIO_MOD_Y_AND_Z 145 
#define  IIO_MOD_Y_OR_Z 144 
#define  IIO_MOD_Z 143 
#define  IIO_NO_MOD 142 
#define  IIO_PH 141 
#define  IIO_PHASE 140 
#define  IIO_POSITIONRELATIVE 139 
#define  IIO_POWER 138 
#define  IIO_PRESSURE 137 
#define  IIO_PROXIMITY 136 
#define  IIO_RESISTANCE 135 
#define  IIO_ROT 134 
#define  IIO_STEPS 133 
#define  IIO_TEMP 132 
#define  IIO_TIMESTAMP 131 
#define  IIO_UVINDEX 130 
#define  IIO_VELOCITY 129 
#define  IIO_VOLTAGE 128 

__attribute__((used)) static bool event_is_known(struct iio_event_data *event)
{
	enum iio_chan_type type = IIO_EVENT_CODE_EXTRACT_CHAN_TYPE(event->id);
	enum iio_modifier mod = IIO_EVENT_CODE_EXTRACT_MODIFIER(event->id);
	enum iio_event_type ev_type = IIO_EVENT_CODE_EXTRACT_TYPE(event->id);
	enum iio_event_direction dir = IIO_EVENT_CODE_EXTRACT_DIR(event->id);

	switch (type) {
	case IIO_VOLTAGE:
	case IIO_CURRENT:
	case IIO_POWER:
	case IIO_ACCEL:
	case IIO_ANGL_VEL:
	case IIO_MAGN:
	case IIO_LIGHT:
	case IIO_INTENSITY:
	case IIO_PROXIMITY:
	case IIO_TEMP:
	case IIO_INCLI:
	case IIO_ROT:
	case IIO_ANGL:
	case IIO_TIMESTAMP:
	case IIO_CAPACITANCE:
	case IIO_ALTVOLTAGE:
	case IIO_CCT:
	case IIO_PRESSURE:
	case IIO_HUMIDITYRELATIVE:
	case IIO_ACTIVITY:
	case IIO_STEPS:
	case IIO_ENERGY:
	case IIO_DISTANCE:
	case IIO_VELOCITY:
	case IIO_CONCENTRATION:
	case IIO_RESISTANCE:
	case IIO_PH:
	case IIO_UVINDEX:
	case IIO_GRAVITY:
	case IIO_POSITIONRELATIVE:
	case IIO_PHASE:
	case IIO_MASSCONCENTRATION:
		break;
	default:
		return false;
	}

	switch (mod) {
	case IIO_NO_MOD:
	case IIO_MOD_X:
	case IIO_MOD_Y:
	case IIO_MOD_Z:
	case IIO_MOD_X_AND_Y:
	case IIO_MOD_X_AND_Z:
	case IIO_MOD_Y_AND_Z:
	case IIO_MOD_X_AND_Y_AND_Z:
	case IIO_MOD_X_OR_Y:
	case IIO_MOD_X_OR_Z:
	case IIO_MOD_Y_OR_Z:
	case IIO_MOD_X_OR_Y_OR_Z:
	case IIO_MOD_LIGHT_BOTH:
	case IIO_MOD_LIGHT_IR:
	case IIO_MOD_ROOT_SUM_SQUARED_X_Y:
	case IIO_MOD_SUM_SQUARED_X_Y_Z:
	case IIO_MOD_LIGHT_CLEAR:
	case IIO_MOD_LIGHT_RED:
	case IIO_MOD_LIGHT_GREEN:
	case IIO_MOD_LIGHT_BLUE:
	case IIO_MOD_LIGHT_UV:
	case IIO_MOD_LIGHT_DUV:
	case IIO_MOD_QUATERNION:
	case IIO_MOD_TEMP_AMBIENT:
	case IIO_MOD_TEMP_OBJECT:
	case IIO_MOD_NORTH_MAGN:
	case IIO_MOD_NORTH_TRUE:
	case IIO_MOD_NORTH_MAGN_TILT_COMP:
	case IIO_MOD_NORTH_TRUE_TILT_COMP:
	case IIO_MOD_RUNNING:
	case IIO_MOD_JOGGING:
	case IIO_MOD_WALKING:
	case IIO_MOD_STILL:
	case IIO_MOD_ROOT_SUM_SQUARED_X_Y_Z:
	case IIO_MOD_I:
	case IIO_MOD_Q:
	case IIO_MOD_CO2:
	case IIO_MOD_ETHANOL:
	case IIO_MOD_H2:
	case IIO_MOD_VOC:
	case IIO_MOD_PM1:
	case IIO_MOD_PM2P5:
	case IIO_MOD_PM4:
	case IIO_MOD_PM10:
		break;
	default:
		return false;
	}

	switch (ev_type) {
	case IIO_EV_TYPE_THRESH:
	case IIO_EV_TYPE_MAG:
	case IIO_EV_TYPE_ROC:
	case IIO_EV_TYPE_THRESH_ADAPTIVE:
	case IIO_EV_TYPE_MAG_ADAPTIVE:
	case IIO_EV_TYPE_CHANGE:
		break;
	default:
		return false;
	}

	switch (dir) {
	case IIO_EV_DIR_EITHER:
	case IIO_EV_DIR_RISING:
	case IIO_EV_DIR_FALLING:
	case IIO_EV_DIR_NONE:
		break;
	default:
		return false;
	}

	return true;
}